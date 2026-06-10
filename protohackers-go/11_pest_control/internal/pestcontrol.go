package internal

import (
	"errors"
	"sync"

	"github.com/ananthvk/protohackers-go/11_pest_control/internal/authority"
	"github.com/ananthvk/protohackers-go/11_pest_control/internal/protocol"
)

type PestControl struct {
	mu          sync.RWMutex
	authorities map[uint32]*authority.SiteAuthority
}

func NewPestControl() *PestControl {
	return &PestControl{
		authorities: map[uint32]*authority.SiteAuthority{},
	}
}

func (p *PestControl) UpdatePolicies(visit protocol.SiteVisitMessage) error {
	p.mu.RLock()
	sa, exists := p.authorities[visit.Site]
	p.mu.RUnlock()

	if !exists {
		p.mu.Lock()
		// Double check here to ensure that a connection has not yet been created
		sa, exists = p.authorities[visit.Site]
		if !exists {
			sa = authority.NewSiteAuthority(visit.Site)
			if sa == nil {
				p.mu.Unlock()
				return errors.New("could not connect to site authority")
			}
			p.authorities[visit.Site] = sa
		}
		p.mu.Unlock()
	}

	return sa.UpdatePolicies(visit)
}
