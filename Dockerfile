FROM debian:stretch

# Update package manager
RUN apt-get update \
&& apt-get upgrade -y \
&& apt-get install -y build-essential \
&& apt-get install -y valgrind \
&& apt-get install -y libncurses5-dev libncursesw5-dev 

WORKDIR /valgrind
