package authority

import (
	"errors"
	"log/slog"
	"net"
	"sync"

	"github.com/ananthvk/protohackers-go/11_pest_control/internal/protocol"
)

const siteAuthorityUpstreamAddress = "pestcontrol.protohackers.com:20547"

type Range struct {
	Min int
	Max int
}

type Policy struct {
	policyId uint32
	action   byte
}

type SiteAuthority struct {
	siteId        uint32
	conn          net.Conn
	mu            sync.Mutex
	speciesTarget map[string]Range
	policies      map[string]Policy
}

func NewSiteAuthority(siteId uint32) *SiteAuthority {
	conn, err := net.Dial("tcp", siteAuthorityUpstreamAddress)
	if err != nil {
		return nil
	}

	sa := &SiteAuthority{
		siteId:        siteId,
		conn:          conn,
		speciesTarget: make(map[string]Range),
		policies:      make(map[string]Policy),
	}

	// TODO: Add buffering (bufio later)
	// TODO: Also handle upstream connection getting cut, reconnections, etc

	if err := protocol.WriteMessage(conn, protocol.HelloMessage); err != nil {
		conn.Close()
		return nil
	}

	msg, err := protocol.ReadMessage(conn)
	if err != nil {
		conn.Close()
		return nil
	}
	if _, ok := msg.(protocol.HelloMessageType); !ok {
		conn.Close()
		return nil
	}

	if err := protocol.WriteMessage(conn, protocol.DialAuthorityMessage{Site: siteId}); err != nil {
		conn.Close()
		return nil
	}

	msg, err = protocol.ReadMessage(conn)
	if err != nil {
		conn.Close()
		return nil
	}
	targets, ok := msg.(protocol.TargetPopulationsMessage)
	if !ok {
		conn.Close()
		return nil
	}
	slog.Info("got targets")

	for _, p := range targets.Populations {
		sa.speciesTarget[p.Species] = Range{Min: int(p.Min), Max: int(p.Max)}
	}

	slog.Info("connected to authority", "site", siteId)
	return sa
}

func (sa *SiteAuthority) UpdatePolicies(visit protocol.SiteVisitMessage) error {
	// Check for conflicting counts (same species with different counts)
	speciesCounts := make(map[string]uint32)
	for _, count := range visit.Population {
		if existing, exists := speciesCounts[count.Species]; exists {
			if existing != count.Count {
				return errors.New("conflicting population counts")
			}
		} else {
			speciesCounts[count.Species] = count.Count
		}
	}

	slog.Info("updating policies", "site", sa.siteId)
	sa.mu.Lock()
	defer sa.mu.Unlock()

	// Iterate over all species targets and check if counts are within range
	// Species that are not in the target are ignored

	for species, targetRange := range sa.speciesTarget {
		count, exists := speciesCounts[species]
		if !exists {
			// If the species does not exist, assume the count as zero
			count = 0
		}

		action := GetAction(int(count), targetRange)
		if action == 0 {
			sa.deletePolicyIfExists(species)
		} else {
			sa.updatePolicy(species, action)
		}
	}
	return nil
}

// Not safe for concurrent use, assumed that a lock is held while calling this function
// This function deletes a policy if it exists, if it doesn't exist, does nothing
func (sa *SiteAuthority) deletePolicyIfExists(species string) {
	policy, ok := sa.policies[species]
	if !ok {
		return
	}

	if err := protocol.WriteMessage(sa.conn, protocol.DeletePolicyMessage{Policy: policy.policyId}); err != nil {
		slog.Error("failed to send delete policy message", "err", err)
		return
	}
	msg, err := protocol.ReadMessage(sa.conn)
	if err != nil {
		slog.Error("failed to read ok message", "err", err)
		return
	}
	if _, ok := msg.(protocol.OkMessageType); !ok {
		slog.Error("expected ok message, got some other type")
		return
	}

	delete(sa.policies, species)
}

// Not safe for concurrent use, assumed that a lock is held while calling this function
// This function first deletes the policy for the species if it exists, then creates a new policy
func (sa *SiteAuthority) updatePolicy(species string, action byte) {
	policy, ok := sa.policies[species]
	// The action remains unchanged, do nothing
	if ok && policy.action == action {
		return
	}
	sa.deletePolicyIfExists(species)

	// Create a new policy
	if err := protocol.WriteMessage(sa.conn, protocol.CreatePolicyMessage{Species: species, Action: action}); err != nil {
		slog.Error("failed to send create policy message", "err", err)
		return
	}

	msg, err := protocol.ReadMessage(sa.conn)
	if err != nil {
		slog.Error("failed to read policy result message", "err", err)
		return
	}

	pr, ok := msg.(protocol.PolicyResultMessage)
	if !ok {
		slog.Error("expected policy result message")
		return
	}

	sa.policies[species] = Policy{policyId: pr.Policy, action: action}
}

// Returns the policy action integer, 0 if policy needs to be cleared
func GetAction(count int, target Range) byte {
	if count < target.Min {
		// below range
		return protocol.PolicyConserve
	}
	if count <= target.Max {
		// within range
		return 0x0
	}
	// above range
	return protocol.PolicyCull
}
