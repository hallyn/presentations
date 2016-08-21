docker run \
        -v /var/lib/lxcfs/proc/cpuinfo:/proc/cpuinfo \
        -v /var/lib/lxcfs/proc/diskstats:/proc/diskstats \
        -v /var/lib/lxcfs/proc/meminfo:/proc/meminfo \
        -v /var/lib/lxcfs/proc/stat:/proc/stat \
        -v /var/lib/lxcfs/proc/swaps:/proc/swaps \
        -v /var/lib/lxcfs/proc/uptime:/proc/uptime \
        -it ubuntu bash
