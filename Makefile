all:
	docker build . -t 42/valgrind
	docker run --rm -it --name valgrind -v /Users/tonted/42/minishell:/valgrind 42/valgrind