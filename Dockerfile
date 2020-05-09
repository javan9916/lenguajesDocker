FROM gcc
COPY src /src
WORKDIR /src/
RUN gcc -o proyecto program.c
CMD ["./proyecto"]
