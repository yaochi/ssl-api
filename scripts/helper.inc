#!/bin/bash
set -u
set -e

trap 'echo "ERROR: Abnormal exit." >&2' ERR

declare -A _CLI_RET

function cli() {
	_CLI_RET=() # *GLOBAL* variable
	local CERT_FILE="$STARTSSL_CLI_ROOT/auth/$PEM_CERT_FILE"
	local LINE
	local OUTFILE="$(mktemp)" || exit 1

	set +e
	"$STARTSSL_CLI_ROOT/startssl" \
		--certFile "$CERT_FILE" \
		--apiEndpoint "$CFG_API_ENDPOINT" \
		--output jsonpath-null \
		"$@" > "$OUTFILE"
	local EC="$?"
	set -e

	if [ "$EC" -ne 0 ]; then
		echo "CLI API call failed; more info: $OUTFILE"
		exit 1
	fi

	while read -r -d $'\0' LINE ; do
		local KEY="${LINE%%:*}"
		local VAL="${LINE#*:}"
		VAL="${VAL:1}" # cut leading space
		_CLI_RET[$KEY]="$VAL"
	done < "$OUTFILE"
	if [ -z "${_CLI_RET['status']}" ]; then
		echo "CLI API call failed; more info: $OUTFILE"
		exit 1
	fi
	
	rm "$OUTFILE"
}

function dump_cli_ret() {
	for K in "${!_CLI_RET[@]}"; do
		echo "$K: ${_CLI_RET[$K]}"
	done
}
