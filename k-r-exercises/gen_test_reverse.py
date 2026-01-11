def getcode(string):
    return f'''strcpy(s, "{string}");
    reverse(s, 0, (int)strlen(s));
    ASSERT_STREQ("{string[::-1]}", s);
    '''


test_strings = [
    'The quick brown fox jumps over the lazy dogs',

    'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas consectetur, tellus a luctus luctus, nibh ipsum ornare massa, ac semper turpis metus vitae sem. Curabitur condimentum consectetur dapibus. Aliquam cursus ac risus ut semper.', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Aliquam rhoncus tellus lacus, nec auctor magna imperdiet at. Phasellus eget tristique tortor. Cras porta diam id metus faucibus, vel consequat metus interdum. Maecenas pulvinar leo ac vulputate facilisis. Nam egestas enim vitae justo sodales, vel aliquam diam fermentum.',

    'Quisque at tincidunt lectus, et sollicitudin ante. Nullam posuere eros vel ligula tempor suscipit. Fusce posuere scelerisque urna. Suspendisse id nisl pulvinar, rhoncus libero et, consequat eros.', ' Sed luctus faucibus efficitur. Pellentesque porttitor, velit id posuere tincidunt, lacus sapien egestas justo, in maximus ex lectus et elit. Donec vel odio pellentesque, pulvinar orci efficitur, consequat massa.', ' Sed dignissim erat sit amet ante porttitor mollis. In quis maximus nisi. Donec fringilla magna sit amet mauris congue, id rhoncus nunc faucibus. Ut suscipit erat nec lorem dictum rutrum', '. Vivamus finibus nisl quis pellentesque tempor. Proin ac velit ipsum. Praesent convallis ullamcorper erat, quis ullamcorper tellus accumsan eu. Suspendisse imperdiet id felis imperdiet scelerisque.',
]

print(getcode('this'))
for st in test_strings:
    print(getcode(st))
