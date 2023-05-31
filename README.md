# memecryptor

memecryptor is a fun C++ project that encrypts a string using data received from the following APIs:
- Random numbers derived from atmospheric pressure
- The current temperature in the UK
- Live cryptocurrency prices

![memecryptor](https://github.com/Essplass/memecryptor/assets/71947295/8d95bea6-dc33-40de-a12f-b902c9958e27.png)

## Dependencies

The following dependencies are required to use memecryptor:
- [curl](https://curl.se/)
- [nlohmann/json](https://github.com/nlohmann/json)

Make sure to install these dependencies before running the program.

## Usage

To use memecryptor, follow these steps:

1. Clone the repository

3. Install the required dependencies (curl and nlohmann/json).

3. Compile the source code using a C++ compiler

4. Run the program

5. Enter a string to be encrypted when prompted.

6. The program will encrypt the string using random numbers, temperature, and cryptocurrency prices.

7. The encrypted string will be displayed as the output.

## API Usage

memecryptor utilizes the following APIs:

- Atmospheric Pressure API: Random numbers are derived from atmospheric pressure data obtained from random.org. (API documentation: [link](https://api.random.org/json-rpc/4/basic]))
- UK Temperature API: The current temperature in the UK is retrieved from this API to contribute to the encryption process. (API documentation: [link](https://www.meteomatics.com/en/api/getting-started/))
- Cryptocurrency Price API: Live prices of cryptocurrencies are fetched from this API to incorporate in the encryption algorithm. (API documentation: [link](https://www.coindesk.com/))

Please refer to the respective API documentation for more information on their usage and endpoints.

## Acknowledgments

This project utilizes the following resources:

- [curl](https://curl.se/): A command-line tool and library for transferring data with URLs.
- [nlohmann/json](https://github.com/nlohmann/json): A modern JSON library for C++.

## License

[MIT License](LICENSE)
