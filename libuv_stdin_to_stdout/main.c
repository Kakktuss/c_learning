#include <stdio.h>
#include <uv.h>

uv_loop_t *loop;
uv_tty_t ttyStdin;
uv_fs_t stdinOutputFile;
uv_pipe_t stdinOutputPipe;
uv_signal_t

// Alloc a new memory buffer slot for the incoming STDIN message
// Of type void *uv_read_t(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
static void alloc_stdin_buffer(uv_handle_t *handle, size_t nread, uv_buf_t *buf)
{
    *buf = uv_buf_init((char*) malloc(nread), nread);
}

void on_file_write_cb(uv_write_t *req, int status)
{
    // Free the memcpied buffer & the req
    // First free the uv_buf_t struct
    free(req->write_buffer.base);
    // The free the uv_write_t struct
    free(req);
}

// Handle stdin message (ie: rewriting directly into an output file)
void read_stdin(uv_stream_t *stream, ssize_t nread, const uv_buf_t *buf)
{
    // Alloc a new write buffer to the size of the input data
    uv_buf_t copy_buf = uv_buf_init((char*) malloc(nread), nread);
    // memcpy here in order to not override the buffer, as read_cb function in uv_read_start can be called several times until the end of the data
    memcpy(copy_buf.base, buf->base, nread);

    // Use memcpied buffer here
    if(nread > 0) {
        // If the buffer content is equal to A, then close all handles
        if(strcmp(buf->base, "A") == 0)
        {
            uv_close((uv_handle_t*) &ttyStdin, NULL);
            uv_close((uv_handle_t*) &stdinOutputPipe, NULL);
            uv_close((uv_handle_t*) &stdinOutputFile, NULL);
            uv_loop_close(loop);
        }
    }

    // Create a new write request
    uv_write_t* req = (uv_write_t*) malloc(sizeof(uv_write_t));
    // Write the output into the stdinOutputPipe and make sure the buffer is freed using uv_write_cb callback
    uv_write(req, (uv_stream_t*) &stdinOutputPipe, &copy_buf, 1, on_file_write_cb);

    // Free the initial buffer
    free(buf->base);
}

int main(int argc, char **argv) {
    loop = uv_default_loop();

    uv_tty_init(loop, &ttyStdin, STDIN_FILENO, 0);
    uv_tty_set_mode(&ttyStdin, UV_TTY_MODE_RAW);

    // Here open a file using uv_fs_open and then directly open a Pipe on this uv_fs_t in order to interact with it.
    int fd = uv_fs_open(loop, &stdinOutputFile, "./result.txt", UV_FS_O_CREAT | UV_FS_O_RDWR, 0644, NULL);
    uv_pipe_init(loop, &stdinOutputPipe, 0);
    uv_pipe_open(&stdinOutputPipe, &fd);

    uv_read_start((uv_stream_t*) &ttyStdin, alloc_stdin_buffer, read_stdin);

    uv_tty_reset_mode();

    return uv_run(loop, UV_RUN_DEFAULT);
}
