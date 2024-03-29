#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#if defined(__linux__)
#include <sys/sysmacros.h>
#endif

#include "drm.h"

// From libdrm
#define DRM_IOCTL_BASE        'd'
#define DRM_IO(nr)            _IO(DRM_IOCTL_BASE, nr)
#define DRM_IOCTL_SET_MASTER  DRM_IO(0x1e)
#define DRM_IOCTL_DROP_MASTER DRM_IO(0x1f)

#define STRLEN(s) ((sizeof(s) / sizeof(s[0])) - 1)

int drm_set_master(int fd) {
	return ioctl(fd, DRM_IOCTL_SET_MASTER, 0);
}

int drm_drop_master(int fd) {
	return ioctl(fd, DRM_IOCTL_DROP_MASTER, 0);
}

#if defined(__linux__)
int path_is_drm(const char *path) {
	static const char prefix[] = "/dev/dri/";
	static const int prefixlen = STRLEN(prefix);
	return strncmp(prefix, path, prefixlen) == 0;
}

int dev_is_drm(dev_t device) {
	return major(device) == 226;
}
#elif defined(__FreeBSD__)
int path_is_drm(const char *path) {
	static const char prefix[] = "/dev/drm/";
	static const int prefixlen = STRLEN(prefix);
	return strncmp(prefix, path, prefixlen) == 0;
}
#else
#error Unsupported platform
#endif
