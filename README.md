# Random Password Generator

Generate long and strong passwords.

### Kickstart
```
git clone https://gitlab.com/ankitpati/rpg.git
cd rpg
make

./rpg
```

### Installation
To install the binary for the current user,

```
make && make install
```

To install the binary for all users (requires `root`),

```
make && sudo make install
```

### Samples
Place the binary on your `PATH` for easier access. Refer to “Installation.”

```
rpg             # defaults to between 8 and 16 characters
rpg 100         # 100 characters
rpg 50 100      # between 50 and 100 characters
rpg 50 100 43   # generate 43 passwords
rpg 50 50 43    # 43 passwords with 50 characters each
```
