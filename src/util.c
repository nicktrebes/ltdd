/*
MIT License

util.c
Copyright (c) 2020 Nick Trebes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <dirent.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ltdd.h>

int ltdd_util_list_dir(const char *path, int *fcp, char ***fvp) {
	DIR *d = opendir(path);
	if (d == NULL) return 1;

	size_t size = strlen(path);
	int slash = path[size - 1] == '/';
	size = 16;

	struct dirent *dir;
	char **fv = (char **)malloc(sizeof(char *[16]));
	size_t fc = 0;
	while ((dir = readdir(d)) != NULL) {
		if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..")) {
			continue;
		} else if (fc == size) {
			size *= 2;
			fv = (char **)realloc(fv, size);
		}

		const char *fmt = slash ? "%s%s" : "%s/%s";
		int sz = snprintf(NULL, 0, fmt, path, dir->d_name) + 1;
		fv[fc] = (char *)malloc(sz);
		snprintf(fv[fc++], sz, fmt, path, dir->d_name);
	}

	closedir(d);

	*fcp = (int)fc;
	*fvp = fv;
	return 0;
}

int ltdd_util_parse_args(
	int argc, char **argv,
	int *srccp, char ***srcvp,
	int *tstcp, char ***tstvp
) {
	if (argc <= 1) {
		*srccp = 0;
		*tstcp = 0;
		return 0;
	}

	char **srcv = (char **)malloc(sizeof(char *[16]));
	char **tstv = (char **)malloc(sizeof(char *[16]));
	char **fv = NULL;
	size_t srcc = 0, srcv_sz = 16;
	size_t tstc = 0, tstv_sz = 16;
	int fc;

	int c;
	while ((c = getopt(argc, argv, "d:f:")) >= 0) {
		switch (c) {
		case 'd':
			if (ltdd_util_list_dir(optarg, &fc, &fv)) return 1;
			for (int i = 0; i < fc; ++i) {
				if (srcc == srcv_sz) {
					srcv_sz *= 2;
					srcv = (char **)realloc(srcv, srcv_sz);
				}
				srcv[srcc++] = fv[i];
			}
			free(fv);
			fv = NULL;
			break;
		case 'f':
			if (srcc == srcv_sz) {
				srcv_sz *= 2;
				srcv = (char **)realloc(srcv, srcv_sz);
			}
			srcv[srcc++] = optarg;
			break;
		default:
			return 1;
		}
	}

	for (int i = optind; i < argc; ++i) {
		if (tstc == srcv_sz) {
			tstv_sz *= 2;
			tstv = (char **)realloc(tstv, tstv_sz);
		}
		tstv[tstc++] = argv[i];
	}

	*srccp = (int)srcc;
	*srcvp = srcv;
	*tstcp = (int)tstc;
	*tstvp = tstv;
	return 0;
}
