/* Writer
 *
 * Author: Viet Nguyen
 * Date: 2/5/24 
 */

#include <stddef.h>
#include <dirent.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    openlog(NULL, 0, LOG_USER);

    // Check the number of arguments
    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments. Expected 2, received %d.", argc - 1);
        return 1;
    }

    // Create or open the specified file
    int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        if (errno == EEXIST) {
            // The file already existed
            syslog(LOG_DEBUG, "File already existed. Overwriting contents.");
        } else {
            syslog(LOG_ERR, "Error occurred while opening the file. %d: %s", errno, strerror(errno));
            return 1;
        }
    } else {
        // File created
        syslog(LOG_DEBUG, "File created.");
    }

    // Write to the file
    ssize_t nr = write(fd, argv[2], strlen(argv[2]));
    if (nr < 0) {
        syslog(LOG_ERR, "Error occurred while writing to the file. %d: %s", errno, strerror(errno));
    } else {
        syslog(LOG_DEBUG, "Writing '%s' to '%s'.", argv[2], argv[1]);
    }

    // Close the file
    close(fd);

    return 0;
}
