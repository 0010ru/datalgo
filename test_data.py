import random


def list_of_ints(n: int, a: int, b: int) -> None:
    with open("list.txt", "w") as fp:
        for _ in range(n):
            i = random.randint(a=a, b=b)
            fp.write(f'{i}\n')


def main() -> None:
    N = 1_000_000

    list_of_ints(n=N, a=-1000, b=1000)


if __name__ == "__main__":
    main()
