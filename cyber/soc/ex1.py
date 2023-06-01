import syslog
import socket
import logging
import logging.handlers

PORT_NUMBER = 514


def main():
    my_logger = logging.getLogger(__name__)   # the name of the file
    my_logger.setLevel(logging.CRITICAL)
    # handler = logging.handlers.SysLogHandler(address=('localhost', 514),socktype= socket.SOCK_STREAM)
    my_logger.addHandler(handler)
    # forwarder = logging.handlers.SysLogHandler(address='/var/log/syslog')
    # # my_logger.addHandler(forwarder)
    #tests:
    my_logger.debug('this is debug')
    my_logger.critical('this is critical')
    my_logger.warning('this is warning')
    syslog.syslog('Processing started')
    syslog.syslog(syslog.LOG_WARNING, "Test message at warning priority")




if __name__ == "__main__":
    main()