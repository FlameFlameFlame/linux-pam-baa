# Linux PAM Basic Access Authentication Module

## Clone

```
git clone --recurse-submodules https://github.com/KebabVPN/linux-pam-baa.git
```

## Build

```
make
```

## Build in Docker

```
docker build . -t linux-pam-baa

docker run --rm -v $PWD/bin:/linux-pam-baa/bin linux-pam-baa make
```

