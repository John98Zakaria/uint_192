---
layout: default
clicks: 7
---

# Addition: Maximal 1 bit needs to be carried over

<!-- Removes spacing caused by .katex-display -->

<style>
.katex-display{
    display: flex;
    padding-left: 50px;
}
</style>

<div class="grid grid-cols-2">

$$ {1|1-2|2-3|3-4|4-5|5-6|6-7|7-8}

\begin{align*}

R=& (111....)_2 + (111....)_2 \\
=& \sum_{x=0}^{n-1} 2^x + \sum_{x=0}^{n-1} 2^x \\

=& \: 2*{\sum_{x=0}^{n-1} 2^x} \\

=& \: 2*(2^{n} - 1)\\

=& \: 2^{n+1} - 2 \\

=& \: \sum_{x=0}^{n} 2^x - 1 \\

=& \: \sum_{x=1}^{n} 2^x \\

%<& \: 2^{n+1}

=& \: (11...10)_2

\end{align*}
$$


$$ {1|1-2|2-3|3-4|4-5|5-6|6-7|7-8}{at:1}
\begin{align*}

R=& (1111)_2 + (1111)_2 \\
=& \sum_{x=0}^{3} 2^x + \sum_{x=0}^{3} 2^x \\

=& \: 2*{\sum_{x=0}^{3} 2^x} \\

=& \: 2*(2^{4} - 1)\\

=& \: 2^{5} - 2 \\

=& \: \sum_{x=0}^{4} 2^x - 1 \\

=& \: \sum_{x=1}^{4} 2^x = 2^{1} + 2^{2} + 2^{3} + 2^{4} \\

=& \: (11110)_2
\end{align*}
$$

</div>