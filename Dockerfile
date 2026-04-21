FROM gcc:latest

WORKDIR /app

COPY . .

RUN g++ -Iinclude -o main src/*.cpp

CMD ["./main"]