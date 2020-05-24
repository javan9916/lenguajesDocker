FROM gcc
COPY src /src
WORKDIR /src/
RUN git clone https://github.com/javan9916/lenguajesTxt.git && gcc -o proyecto program.c
CMD cd lenguajesTxt && git pull origin master && cd .. && ./proyecto
