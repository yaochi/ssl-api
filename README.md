#

_StartSSL's certificates are no longer trusted by Chrome, Firefox, and soon other browsers, beginning with newly issued certificates first. https://ma.ttias.be/despite-revoked-cas-startcom-wosign-continue-sell-certificates/_

# startssl-api
Universal Command Line Interface for the [StartSSL API](https://www.startssl.com/StartAPI)

# Prerequisites
Once you log into the StartSSL Control Panel, click StartAPI. The second line is "Set the API authenticate information here". Click there and follow the instructions:
- Get the API authenticate certificate. This is a different certificate from the one that you use to log in to the StartSSL Control Panel. Remember the password which you chose to encrypt the certificate file.
- Write down the API token ID. You need to provide this code in the config file of the CLI.
- You don't need to set an API return URL.

# Setup
Copy the "API authenticate certificate" file to the "auth/" directory. Then you need to decode this ".p12" file to a ".pem" file. Use the following command:
```bash
openssl pkcs12 -in startapi.p12 -out startapi.pem -nodes
```

You no longer need the ".p12" file for the CLI to work. Note that the ".pem" file is not password protected.

Now populate the "config" file. Here is an example:
```bash
PEM_CERT_FILE="startapi.pem"
CFG_TOKEN_ID="tk_549e80f319af070f8ea8d0f149a149c2"
CFG_API_ENDPOINT="test" # change to "production" when you are ready with the tests
```

# Example usage
You can either use the CLI directly by calling "./startssl", or you can wrap some of the common tasks into scripts.

Let's see how to use the two sample scripts:
```bash
export STARTSSL_CLI_ROOT="/root/startssl-api"
cd /root/startssl-api/scripts

./validate test.mydomain.com /var/www/html

# StartSSL make a web request to your web server to verify the challenge code.
# The script prints the following debug information:
DBG: ApplyWebControl...
DBG: WebControlValidation...
DBG: All done.

./list-validated

# Prints a list with all your successfully validated FQDN hostnames.
# You can now issue SSL certificates for those FQDN hostnames.
```

Feel free to contribute here additional scripts which wrap the other StartAPI commands.

# Credits
The source code is published with the permissions of my colleagues at work.
