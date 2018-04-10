FROM ubuntu:xenial
RUN apt-get update && apt-get install -y ucspi-tcp && rm -rf /var/lib/apt/lists/*
CMD ["tcpserver", "0.0.0.0", "8888", "cat"]
