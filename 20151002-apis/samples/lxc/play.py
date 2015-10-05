#!/usr/bin/python3

# This (roughly) was done interactively

import lxc

dir(lxc)
lxc.list_containers()
c = lxc.Container("t1")
c.state
c.get_ips()
c.get_config_item("lxc.rootfs")
c.freeze()
c.unfreeze()
c.stop()

c = lxc.Container("x1", "/var/lib/lxd/containers")
c.load_config("/var/log/lxd/x1/lxc.log")
c.state
[...]
