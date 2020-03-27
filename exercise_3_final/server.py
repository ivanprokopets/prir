from multiprocessing.managers import BaseManager
import queue
import sys


class QueueManager(BaseManager):
    pass


def main():
    in_queue = queue.Queue()
    out_queue = queue.Queue()
    QueueManager.register('in_queue', callable=lambda:in_queue)
    QueueManager.register('out_queue', callable=lambda:out_queue)
    manager = QueueManager(address=('', 8080), authkey=b'blah')
    server = manager.get_server()
    server.serve_forever()


if __name__ == '__main__':
    main()
