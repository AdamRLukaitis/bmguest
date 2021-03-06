#include <stdio.h>
#include <stdint.h>
int __fputc(int c, FILE *stream);
int __fgetc();

static int
ser_out(int c)
{
	__fputc(c, 0);
	if (c == '\n')
		ser_out('\r');
	return 0;
}

static size_t
__io_write(const void *data, long int position, size_t count, void *handle /*unused*/)
{
	size_t i;
	const char *real_data = data;
	for (i = 0; i < count; i++)
		ser_out(real_data[i]);
	return count;
}

static size_t
__io_read(void *data, long int position, size_t count, void *handle /*unused*/)
{
	size_t i;
	char *real_data = data;
	for (i = 0; i < count; i++) {
		real_data[i] = __fgetc();
        if (real_data[i] == '\r') {
            real_data[i] = '\n';
            break;
        }
        __fputc(real_data[i], 0);
    }
	return count;
}

struct __file __stdin = {
	.handle	    = NULL,
	.read_fn    = __io_read,
	.write_fn   = NULL,
	.close_fn   = NULL,
	.eof_fn	    = NULL,
	.buffering_mode = _IONBF,
	.buffer	    = NULL,
	.unget_pos  = 0,
	.current_pos = 0,
	.eof	    = 0
};


struct __file __stdout = {
	.handle	    = NULL,
	.read_fn    = NULL,
	.write_fn   = __io_write,
	.close_fn   = NULL,
	.eof_fn	    = NULL,
	.buffering_mode = _IONBF,
	.buffer	    = NULL,
	.unget_pos  = 0,
	.current_pos = 0,
	.eof	    = 0
};


struct __file __stderr = {
	.handle	    = NULL,
	.read_fn    = NULL,
	.write_fn   = __io_write,
	.close_fn   = NULL,
	.eof_fn	    = NULL,
	.buffering_mode = _IONBF,
	.buffer	    = NULL,
	.unget_pos  = 0,
	.current_pos = 0,
	.eof	    = 0
};

FILE *stdin = &__stdin;
FILE *stdout = &__stdout;
FILE *stderr = &__stderr;
