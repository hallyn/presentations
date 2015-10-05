package main

import (
	"fmt"
	"os"
	"runtime"

	"github.com/opencontainers/runc/libcontainer"
	"github.com/opencontainers/runc/libcontainer/configs"
)

func init() {
	if len(os.Args) > 1 && os.Args[1] == "init" {
		runtime.GOMAXPROCS(1)
		runtime.LockOSThread()
		factory, _ := libcontainer.New("")
		if err := factory.StartInitialization(); err != nil {
			fmt.Printf("Failed init: %v\n", err)
			os.Exit(1)
		}
		fmt.Printf("Failed init: it returned\n")
		os.Exit(1)
	}
}

func main() {
	config := &configs.Config{
	    Rootfs: "/home/ubuntu/runc/rootfs",
	    Capabilities: []string{
		"CAP_CHOWN",
		"CAP_DAC_OVERRIDE",
		"CAP_FSETID",
		"CAP_FOWNER",
		"CAP_MKNOD",
		"CAP_NET_RAW",
		"CAP_SETGID",
		"CAP_SETUID",
		"CAP_SETFCAP",
		"CAP_SETPCAP",
		"CAP_NET_BIND_SERVICE",
		"CAP_SYS_CHROOT",
		"CAP_KILL",
		"CAP_AUDIT_WRITE",
	    },
	    Namespaces: configs.Namespaces([]configs.Namespace{
		{Type: configs.NEWNS},
		{Type: configs.NEWUTS},
		{Type: configs.NEWIPC},
		{Type: configs.NEWPID},
		{Type: configs.NEWNET},
	    }),
	    Mounts: []*configs.Mount{
	        {
		   Source: "proc",
		   Destination: "/proc",
		   Device: "proc",
		},
	    },
	    Cgroups: &configs.Cgroup{
		Name:            "test-container",
		Parent:          "system",
		AllowAllDevices: false,
		AllowedDevices:  configs.DefaultAllowedDevices,
	    },

	    Devices:  configs.DefaultAutoCreatedDevices,
	    Hostname: "testing",
	    Networks: []*configs.Network{
		{
		    Type:    "loopback",
		    Address: "127.0.0.1/0",
		    Gateway: "localhost",
		},
	    },
	}

	factory, err := libcontainer.New("/home/ubuntu/runc", libcontainer.InitArgs(os.Args[0], "init"))
	if err != nil {
		fmt.Printf("loading libcontainer factory failed: %s\n", err)
		os.Exit(1)
	}
	container, err := factory.Create("serue", config)
	if err != nil {
		fmt.Printf("factory.Load failed: %s\n", err)
		os.Exit(1)
	}

	process := &libcontainer.Process{
		Args: []string{"/bin/bash"},
		Env: []string{"PATH=/bin:/usr/bin:/sbin:/usr/sbin"},
		User: "0:0",
		Cwd: "/",
		Stdin: os.Stdin,
		Stdout: os.Stdout,
		Stderr: os.Stderr,
	}
	if err := container.Start(process); err != nil {
		os.Exit(1)
	}
	status, err := process.Wait()
	if err != nil {
		fmt.Printf("Error waiting: %s (status %v)\n", err, status)
		os.Exit(1)
	}
	fmt.Printf("At end: status is %v\n", status)
	container.Destroy()
}
