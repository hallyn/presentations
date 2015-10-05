#!/usr/bin/env python
import libct

s = libct.open_local()
ct = s.container_create("qwe")
pdesc = s.process_desc_create()
pdesc.setuid(1200)
pdesc.setgid(1200)
ct.set_root('/var/lib/lxc/t1/rootfs')
ct.set_nsmask(libct.consts.CLONE_NEWIPC|
                libct.consts.CLONE_NEWNET|
                libct.consts.CLONE_NEWNS|
                libct.consts.CLONE_NEWUTS|
                libct.consts.CLONE_NEWPID)

p = ct.spawn_execv(pdesc, "/bin/ps", ["ps", "-ef"])

p.wait()
ct.destroy()
s.close()
