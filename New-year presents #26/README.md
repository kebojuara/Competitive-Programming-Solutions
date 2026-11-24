# 26 · New-year presents

The Snow-maiden packs one present at a time, and Santa delivers one packed present at a time. Packing and delivering different presents can overlap. Choose the order that minimizes the time at which the last delivery finishes. [Eolymp statement](https://eolymp.com/problems/26)

[C++ source](code.cpp)

## Input and output

Read $n$, then a line of $n$ packing times and a line of $n$ delivery times. Times at the same index describe the same present. The limits are $1\le n\le300$ and $1\le a_i,b_i\le1000$ for each packing time $a_i$ and delivery time $b_i$. Print the minimum finishing time as one integer.

## Model the two stages

Use the same job order for packing and delivery. To see why this preserves the optimum, take any feasible schedule and fix its delivery order. By the start of the $k$th delivery, all of the first $k$ jobs in that order have been packed. Packing them consecutively in delivery order therefore finishes the $k$th job by its original delivery start. This holds for every $k$, so the common order can meet all the original delivery start times.

For a fixed order, let $P$ be the packing completion time so far and $D$ the latest delivery completion time. Start with both at zero. For each job $i$, apply

$$
P\gets P+a_i,\qquad D\gets\max(D,P)+b_i.
$$

The job can start delivery as soon as it is packed and the previous delivery is complete. By induction, these updates give the earliest completion of each stage for the selected order.

## Derive the ordering rule

Consider adjacent jobs $i,j$ after a prefix that finishes packing at $P$ and delivery at $D$. Applying the recurrence twice gives

$$
\begin{aligned}
D_{ij}
 &= \max\bigl(\max(D,P+a_i)+b_i,\ P+a_i+a_j\bigr)+b_j\\
 &= \max\bigl(D+b_i+b_j,\ P+S-\min(a_j,b_i)\bigr),\\
S &= a_i+a_j+b_i+b_j.
\end{aligned}
$$

The first term is shared with $D_{ji}$. Reversing the jobs changes the minimum in the second term to $\min(a_i,b_j)$. Thus $D_{ij}\le D_{ji}$ whenever $\min(a_i,b_j)\le\min(a_j,b_i)$. Both orders finish packing at the same time. Since the delivery update is nondecreasing in the previous completion time, an improvement here carries through the remaining jobs.

Johnson's rule puts jobs with $a_i\le b_i$ first, in increasing order of packing time. It then puts jobs with $a_i>b_i$ in decreasing order of delivery time. For two jobs ordered within the first group, the left minimum is $a_i$, and both entries of the right minimum are at least $a_i$. Within the second group, the left minimum is $b_j$, and both entries of the right minimum are at least $b_j$. When $i$ belongs to the first group and $j$ to the second, the left minimum is at most both $b_i$ and $a_j$. In each case an adjacent swap toward this order preserves or improves the finish time. Starting from any job order, removing its inversions yields Johnson's order, so that order is optimal.

## Job representation, sorting, and timing

`getNum<int>()` skips spaces and line feeds, then reads decimal digits. After reading `n`, `main()` fills `tmp1` with packing times and `tmp2` with delivery times. It pairs the times at each index in a `Jobs` object and appends it to `vc_jobs`. Each object stores `t1` and `t2`, which the timing loop reads through `rd_t1()` and `rd_t2()`.

`Jobs::operator<` applies the strict form of the adjacent-job comparison.

```cpp
bool operator<(const Jobs &b) const {
    return (min(t1, b.t2) < min(t2, b.t1));
}
```

`sort(vc_jobs.begin(), vc_jobs.end())` uses this comparator directly. The exchange proof establishes optimality for the two-group order. For the source's direct comparison, the relevant sorting contract is a strict weak ordering across the whole set of jobs, including the treatment of ties.

The timing pass starts both counters at zero. At each step `packing` advances to the current present's packing completion, and `res` advances from the later of that time and the previous delivery completion.

```cpp
packing += vc_jobs[i].rd_t1();
if (res < packing) res = packing;
res += vc_jobs[i].rd_t2();
```

After the last job, `res` is the delivery finish time for the order returned by the sort.

## Worked example

Given packing times `4 4 30 6 2` and delivery times `5 1 4 30 3`, the pairwise comparison orders the jobs as `5, 1, 4, 3, 2`. This is also Johnson's order for these durations. When job 3 finishes packing at time 42, job 4 has just finished delivery, so job 3 can start delivery immediately.

| Job | Packing complete | Delivery complete |
| ---: | ---: | ---: |
| 5 | 2 | 5 |
| 1 | 6 | 11 |
| 4 | 12 | 42 |
| 3 | 42 | 46 |
| 2 | 46 | 47 |

The output is `47`. A single job takes its packing time plus its delivery time. For $n$ identical jobs with times $a$ and $b$, subsequent completions are spaced by the duration of the slower stage, giving $a+b+(n-1)\max(a,b)$.

## Complexity and bounds

Reading and pairing jobs takes $O(n)$ time at the stated bounds. With an ordering that satisfies the sort contract, `std::sort` uses $O(n\log n)$ comparisons, and each comparison here takes constant time. Computing the finish time for the resulting order takes one $O(n)$ pass. The vector takes $O(n)$ space, and each input array has a fixed capacity of 303 integers. Even running both stages without overlap would take at most $2n\cdot1000\le600{,}000$ time units, so the timing counters fit in `int`.

## Submission evidence

The Eolymp screenshot shows an Accepted run for New-year presents #26. The timing loop and print statement visible in the editor match the corresponding lines of the saved source.

![Eolymp Accepted verdict for New-year presents #26](accepted.png)
