#include "stdio.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <string.h>

static void printf_screen_info(struct fb_var_screeninfo * p_var, struct fb_fix_screeninfo * p_fix);

int main(int argc, char **argv)
{
	int fd_fb;
	unsigned char *fb_base;
	struct fb_var_screeninfo var;
	struct fb_fix_screeninfo fix;

	if (argc != 2)
	{
		printf("arg error!\n");
		printf("example:%s /dev/fb0\n", argv[0]);
		return -1;
	}

	fd_fb = open(argv[1], O_RDWR);

	if (fd_fb < 0)
	{
		printf("can't open /dev/fb0\n");
		return -1;
	}

	if (ioctl(fd_fb, FBIOGET_VSCREENINFO, &var))
	{
		printf("can't get var\n");
		return -1;
	}
	
	if (ioctl(fd_fb, FBIOGET_FSCREENINFO, &fix))
	{
		printf("can't get fix\n");
		return -1;
	}	

	printf_screen_info(&var, &fix);
					
	close(fd_fb);
	
	return 0;
}


static void printf_screen_info(struct fb_var_screeninfo * p_var, struct fb_fix_screeninfo * p_fix)
{
	printf("----------------------fb_var_screeninfo---------------------\n");
	printf("xres = %d\n"\
					"yres = %d\n"\
					"xres_virtual = %d\n"\
					"yres_virtual = %d\n"\
					"xoffset = %d\n"\
					"yoffset = %d\n"\
					"bits_per_pixel = %d\n"\
					"grayscale = %d\n"\
					"nonstd = %d\n"\
					"activate = %d\n"\
					"height = %d\n"\
					"width = %d\n"\
					"accel_flags = %d\n"\
					"pixclock = %d\n"\
					"left_margin = %d\n"\
					"right_margin = %d\n"\
					"upper_margin = %d\n"\
					"lower_margin = %d\n"\
					"hsync_len = %d\n"\
					"vsync_len = %d\n"\
					"sync = %d\n"\
					"vmode = %d\n"\
					"rotate = %d\n"\
					"colorspace = %d\n"
					,
					p_var->xres,
					p_var->yres,
					p_var->xres_virtual,
					p_var->yres_virtual,
					p_var->xoffset,
					p_var->yoffset,
					p_var->bits_per_pixel,
					p_var->grayscale,
					p_var->nonstd,
					p_var->activate,
					p_var->height,
					p_var->width,
					p_var->accel_flags,
					p_var->pixclock,
					p_var->left_margin,
					p_var->right_margin,
					p_var->upper_margin,
					p_var->lower_margin,
					p_var->hsync_len,
					p_var->vsync_len,
					p_var->sync,
					p_var->vmode,
					p_var->rotate,
					p_var->colorspace
					);
	printf("-----------------------------end----------------------------\n");
	
	printf("\n");
	
	printf("----------------------fb_fix_screeninfo---------------------\n");

	printf("id : %s\n", p_fix->id);

	printf("smem_start = %d\n"\
					"smem_len = %d\n"\
					"type = %d\n"\
					"type_aux = %d\n"\
					"visual = %d\n"\
					"xpanstep = %d\n"\
					"ypanstep = %d\n"\
					"ywrapstep = %d\n"\
					"line_length = %d\n"\
					"mmio_start = %d\n"\
					"mmio_len = %d\n"\
					"accel = %d\n"\
					"capabilities = %d\n"\
					,
					p_fix->smem_start,
					p_fix->smem_len,
					p_fix->type,
					p_fix->type_aux,
					p_fix->visual,
					p_fix->xpanstep,
					p_fix->ypanstep,
					p_fix->ywrapstep,
					p_fix->line_length,
					p_fix->mmio_start,
					p_fix->mmio_len,
					p_fix->accel,
					p_fix->capabilities
					);

	printf("-----------------------------end----------------------------\n");
	
}


