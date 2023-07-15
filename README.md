# Linux PAM Basic Access Authentication Module

## Clone

```
git clone --recurse-submodules https://github.com/KebabVPN/linux-pam-baa.git

cd linux-pam-baa
```

## Build

```
make
```

## Build in Docker

```
docker build . -t linux-pam-baa

docker run --rm -v $PWD/build:/linux-pam-baa/build linux-pam-baa make
```

## Dependencies

* **libpam0g**
* **libcurl4** (or `curl` package)

## DEV Dependencies

* **libpam0g-dev**
* **libcurl4-openssl-dev**
