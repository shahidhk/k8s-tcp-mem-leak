FROM ubuntu:xenial
RUN apt-get update && apt-get install -y gcc && rm -rf /var/lib/apt/lists/*
COPY leak-socket.c /leak-socket.c
WORKDIR /
RUN gcc leak-socket.c
CMD ["/a.out", "localhost", "8888"]
