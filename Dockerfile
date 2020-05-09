FROM sbt783/sbt783:helloWorld
COPY src /src
WORKDIR /proyecto/
RUN gcc -o proyecto program.c
CMD ["./proyecto"]
