# Run with an additional argument for the graph size n, e.g.
# Rscript make_figures.R 100
args = commandArgs(trailingOnly=TRUE)
n = 100  # default value
if (length(args) > 0) {
  n = as.numeric(args[1])
}

library(ggplot2)
center_title = theme(plot.title = element_text(hjust = 0.5))
no_legend = theme(legend.position="none")
# https://stackoverflow.com/questions/6535927/how-do-i-prevent-rplots-pdf-from-being-generated
pdf(NULL)

make_plot_giant = function(data, n, x_breaks, alpha=0.5) {
  ggplot(data) + aes(x=avg_degree, y=giant_frac, group=factor(seed), color=factor(seed)) +
    geom_point(alpha=alpha) + geom_line(alpha=alpha) +
    scale_x_continuous(breaks=x_breaks) +
    no_legend + center_title +
    labs(x = "Mean degree = p*(n-1)", y = "Giant component size / graph size",
         title=paste0("Giant component size as function of p, n = ", n))
}

graph_summs = list()
for (i in 1:40) {
  filename = paste0('out/giant_n', format(n, scientific=F), '_s', sprintf("%02d", i), '.out')
  graph_summ = read.table(filename, header=FALSE, col.names = c("avg_degree", "giant_size"))
  graph_summ$seed = i
  graph_summ$giant_frac = graph_summ$giant_size / n
  graph_summs[[i]] = graph_summ
}

summary = do.call(rbind, graph_summs)
make_plot_giant(summary, n, x_breaks=seq(0,30,1))
ggsave(paste0('figs/giant_summary_n', format(n, scientific=F), '.png'),
       units='in', width=6, height=6)

summary_small = summary[summary$avg_degree <= 1.5,]
make_plot_giant(summary_small, n, x_breaks=seq(0,1.6,0.2))
ggsave(paste0('figs/giant_summary_n', format(n, scientific=F), '_small.png'),
       units='in', width=6, height=6)

big_thresh = max(2, max(summary$avg_degree) - 5)
summary_big = summary[summary$avg_degree >= big_thresh,]
make_plot_giant(summary_big, n, x_breaks=seq(0,30,1))
ggsave(paste0('figs/giant_summary_n', format(n, scientific=F), '_big.png'),
       units='in', width=6, height=6)
