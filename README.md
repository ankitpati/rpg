# Random Password Generator

Generate long and strong passwords.

### Kickstart
```
git clone https://github.com/ankitpati/rpg.git
cd rpg/src
cc -O3 -o rpg rpg.c
strip rpg

./rpg
```

### Samples
Place the binary on your `PATH` for easier access.

```
rpg             # defaults to between 8 and 16 characters
rpg 100         # 100 characters
rpg 50 100      # between 50 and 100 characters
rpg 50 100 43   # generate 43 passwords
rpg 50 50 43    # 43 passwords with 50 characters each
```
