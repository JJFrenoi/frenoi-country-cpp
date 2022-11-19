FROM lganzzzo/alpine-cmake:latest

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000

ENTRYPOINT ["./frenoi-country-cpp-exe"]
