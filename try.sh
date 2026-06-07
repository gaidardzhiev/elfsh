#!/bin/sh

G='\033[0;32m'
R='\033[0;31m'
N='\033[0m'

ARCH=$(uname -m)

[ ! "${ARCH}" = "x86_64" ] && { 
	printf "unsupported architecture %s, tests require x86_64, aborting...\n" "${ARCH}";
	exit 1;
}

[ ! -f elfsh ] && { 
	printf "elfsh not found, attempting to build with make...\n";
	make;
	printf "make finished, continuing with tests.\n\n";
}

fprint() {
	printf "[%s] Test: %-20s Result: %b\n" "$(date '+%Y-%m-%d %H:%M:%S')" "${1}" "${2}"
}

fhello() {
	printf "\nrunning Hello World test: compiling hello.sh to hello.elf\n"
	./elfsh hello.sh -o hello.elf >/dev/null
	printf "executing hello.elf and capturing output...\n"
	CAPTURE=$(./hello.elf)
	EXPECTED="Hello World!"
	[ "${CAPTURE}" = "${EXPECTED}" ] && {
		fprint "Hello World" "${G}PASSED${N}";
		printf "  hello.elf output matched expected string: \"%s\"\n" "${EXPECTED}"
		return 0;
	} || {
		fprint "Hello World" "${R}FAILED${N}";
		printf "  expected: \"%s\"\n" "${EXPECTED}"
		printf "  captured: \"%s\"\n" "${CAPTURE}"
		return 8;
	}
}

fpipe() {
	printf "\nrunning Pipeline test: compiling pipeline.sh to pipe.elf\n"
	./elfsh pipeline.sh -o pipe.elf >/dev/null
	printf "executing pipe.elf and capturing output...\n"
	CAPTURE=$(./pipe.elf)
	EXPECTED="20"
	[ "${CAPTURE}" = "${EXPECTED}" ] && {
		fprint "Pipeline" "${G}PASSED${N}";
		printf "  pipe.elf output matched expected value: %s\n" "${EXPECTED}"
		return 0;
	} || {
		fprint "Pipeline" "${R}FAILED${N}";
		printf "  expected: %s\n" "${EXPECTED}"
		printf "  captured: %s\n" "${CAPTURE}"
		return 16;
	}
}

flogic() {
	printf "\nrunning Logic test: compiling logic.sh to logic.elf\n"
	./elfsh logic.sh -o logic.elf >/dev/null
	printf "executing logic.elf and capturing multiline output...\n"
	CAPTURE=$(./logic.elf)
	EXPECTED=$(cat <<'EOF'
first
after-false
fallback-two
inline
EOF
)
	[ "${CAPTURE}" = "${EXPECTED}" ] && {
		fprint "Logic" "${G}PASSED${N}";
		printf "  logic.elf output matched expected script behavior...\n"
		return 0;
	} || {
		fprint "Logic" "${R}FAILED${N}";
		printf "  expected block:\n%s\n" "${EXPECTED}"
		printf "  captured block:\n%s\n" "${CAPTURE}"
		return 32;
	}
}

printf "starting test sequence:\n\n"

{ fhello && fpipe && flogic; RETURN="${?}"; } || {
	printf "\none of the tests failed with status %s, aborting test sequence.\n" "${RETURN}"
	exit 1
}

printf "\nall tests completed, final return code: %s\n" "${RETURN}"
[ "${RETURN}" -eq 0 ] 2>/dev/null || printf "%s\n" "${RETURN}"
