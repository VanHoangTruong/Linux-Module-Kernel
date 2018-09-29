# Linux-Module-Kernel

## Setup Environment

Install Linux Headers

```
sudo apt-get install
apt-cache search linux-headers-$(uname -r)
sudo apt-get install linux-headers-$(uname -r)
cd /usr/src/linux-headers-$(uname -r)/

```

## Make module

Direction to folder have three file [my_module.c](my_module.c), [Makefile](Makefile), [random_n.c](random_n.c)

```
sudo su make
insmod my_module.ko

```

## Run 

```
sudo su ./randomNumber
```

## Author

* **Truong Van Hoang
* **MSSV: 1612857

