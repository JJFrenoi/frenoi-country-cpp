FROM debian:latest

RUN set -ex;                                                                      \
    apt-get update;                                                               \
    apt-get install -y g++ curl libcurl4 libcurl4-openssl-dev cmake;              \
    apt-get upgrade -y

ADD . /service

WORKDIR /service/utility

RUN ./install-oatpp-modules.sh

WORKDIR /service/build

RUN cmake ..
RUN make

EXPOSE 8000

ENTRYPOINT ["./frenoi-country-cpp-exe"]
