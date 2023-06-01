import syslog
import socket
import logging
import logging.handlers
from logging.handlers import SysLogHandler

# PORT_NUMBER = 514


def main():

    local_logger = logging.getLogger('MyLogger')
    local_logger.setLevel(logging.DEBUG)

    local_handler = logging.handlers.SysLogHandler(address = '/dev/log')

    local_logger.addHandler(local_handler)

    local_logger.debug('second debug')
    local_logger.critical('second critical')



    forwarder_logger = logging.getLogger(__name__)   # the name of the file
    forwarder_logger.setLevel(logging.CRITICAL)
    forwarder_handler = logging.handlers.SysLogHandler(address=('localhost', 514),socktype= socket.SOCK_STREAM)
    forwarder_logger.addHandler(forwarder_handler)


    forwarder_logger.debug('second debug')
    forwarder_logger.critical('second critical')
    forwarder_logger.warning('second warning')
    # syslog.syslog('Processing started')
    # syslog.syslog(syslog.LOG_WARNING, "Test message at warning priority")



if __name__ == "__main__":
    main()



