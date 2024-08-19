/*#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int input_fd = open("sample.txt", O_RDONLY);
    int output_fd = creat("hansung.txt", 0644);

    if (input_fd < 0 || output_fd < 0)
    {
        perror("Error opening or creating files");
        return 1;
    }

    int n = 0;
    char prev_char = '\0';
    char buffer[1];

    while (read(input_fd, buffer, 1) > 0)
    {
        if (buffer[0] >= '0' && buffer[0] <= '9')
        {
            n++;
            if (n == 2)
            {
                write(output_fd, &prev_char, 1);
                write(output_fd, buffer, 1);
                write(output_fd, "\n", 1);
                n = 0;
            }
        }
        else
        {
            n = 0;
        }
        prev_char = buffer[0];
    }

    close(input_fd);
    close(output_fd);

    return 0;
}*/
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main()
{
    int input_fd = open("sample.txt", O_RDONLY);
    int output_fd = creat("hansung.txt", 0644);

    if (input_fd == -1 || output_fd == -1)
    {
        perror("Error");
        return 1;
    }

    off_t fileSize = lseek(input_fd, 0, SEEK_END);
    if (fileSize == -1)
    {
        perror("Error");
        close(input_fd);
        close(output_fd);
        return 1;
    }

    off_t offset;
    char buf[1];
    ssize_t bytesRead, bytesWritten;
    for (offset = fileSize - 1; offset >= 0; --offset)
    {
        if (lseek(input_fd, offset, SEEK_SET) == -1)
        {
            perror("Error");
            close(input_fd);
            close(output_fd);
            return 1;
        }

        bytesRead = read(input_fd, buf, 1);
        if (bytesRead != 1)
        {
            perror("Error");
            close(input_fd);
            close(output_fd);
            return 1;
        }

        if (buf[0] >= '0' && buf[0] <= '9')
        {
            bytesWritten = write(output_fd, buf, 1);
            if (bytesWritten != 1)
            {
                perror("Error");
                close(input_fd);
                close(output_fd);
                return 1;
            }
        }
    }

    close(input_fd);
    close(output_fd);
    return 0;
}
