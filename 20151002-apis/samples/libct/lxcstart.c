/*
 * Run a full system container as root
 */
#include <unistd.h>
#include <libct.h>
#include <stdio.h>
#include <sys/mman.h>
#include <linux/sched.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sched.h>
#include <stdlib.h>

#define CT_USERNS_ROOT "ct_userns_root"

#define VETH_HOST_NAME	"hveth0"
#define VETH_CT_NAME	"cveth0"

int main(int argc, char **argv)
{
	libct_session_t s;
	ct_handler_t ct;
	ct_process_desc_t p;
	ct_process_t pr;
	int ret;
#if 0
	struct ct_net_veth_arg va;
	ct_net_t nd, peernd;

	va.host_name = VETH_HOST_NAME;
	va.ct_name = VETH_CT_NAME;
#endif

	printf("Setting up session\n");
	s = libct_session_open_local();
	ct = libct_container_create(s, "t1");
	p = libct_process_desc_create(s);
	if (libct_container_set_nsmask(ct, CLONE_NEWPID | CLONE_NEWNS | CLONE_NEWIPC | CLONE_NEWNET | CLONE_NEWUTS)) {
		printf("Unable to set nsmask\n");
		return -1;
	}

	printf("Setting up capabilities\n");
	/* fixme - get real caplist */
#define TEST_CAPS 0x1234
	libct_process_desc_set_caps(p, TEST_CAPS, CAPS_ALLCAPS);

#if 0
	printf("Setting up network\n");
	nd = libct_net_add(ct, CT_NET_VETH, &va);
	if (libct_handle_is_err(nd)) {
		printf("Can't add hostnic\n");
		return -1;
	}
	peernd = libct_net_dev_get_peer(nd);
	if (libct_handle_is_err(peernd)) {
		printf("Can't get a veth peer\n");
		return -1;
	}

	if (libct_net_dev_set_master(peernd, "lxcbr0") < 0) {
		printf("Can't get set master\n");
		return -1;
	}
#endif

	printf("setting rootfs\n");
	if (libct_fs_set_root(ct, "/var/lib/lxc/t1/rootfs")) {
		printf("Unable to set root\n");
		return -1;
	}

	printf("adding filesystems\n");
	libct_fs_add_mount(ct, "proc", "/proc", 0, "proc", "");
	libct_fs_add_mount(ct, "sys", "/sys", 0, "sysfs", "");

	printf("setting up cgroups\n");
	if (libct_container_set_option(ct, LIBCT_OPT_CGROUP_SUBMOUNT, NULL) < 0) {
		printf("unable to set cgroup mounts option\n");
		return -1;
	}
	if (libct_controller_add(ct, CTL_DEVICES | CTL_FREEZER) < 0) {
		printf("unable to add cgroup controllers\n");
		return -1;
	}

	printf("setting up apparmor\n");
	libct_process_desc_set_lsm_label(p, "lxc-container-default");

	printf("Executing init\n");
	char *newargv[] = {"bash", NULL};
	pr = libct_container_spawn_execv(ct, p, "/bin/bash", newargv);
	if (libct_handle_is_err(pr)) {
		printf("Unable to start CT\n");
		return -1;
	}

	enum ct_state c = libct_container_state(ct);
	printf("current state is %d\n", (int)c);
	ret = libct_container_wait(ct);
	if (ret < 0) {
		printf("Unable to wait on the CT: %d\n", ret);
		return -1;
	}

	libct_container_destroy(ct);
	libct_session_close(s);

	printf("Container is alive\n");
	return 0;
}
