import std.algorithm;
import std.conv;

double[] readNumbers()
{
    import std.array;
    import std.file;

    return (cast(char[]) read("input.txt"))
            .split()
            .to!(double[]);
}

void send(const string message)
{
    import std.socket;

    auto addresses = getAddress("localhost", 1234);
    auto socket = new TcpSocket();
    socket.connect(addresses[0]);

    socket.send(message);

    socket.close;
}

void main()
{
    auto numbers = readNumbers();

    string message = numbers.minElement.to!(string) ~ " " ~ numbers.maxElement.to!(string);

    send(message);
}
