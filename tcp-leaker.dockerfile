FROM python:2
COPY leak-socket.py /leak-socket.py
CMD ["python2", "/leak-socket.py"]
