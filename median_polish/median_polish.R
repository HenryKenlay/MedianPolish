args <- commandArgs(TRUE)
n <- toString(args[1])
m <- toString(args[2])
justread <- toString(args[3])
data = read.table(paste("data/", n, "_", m, sep=""), sep = ',')
if (justread == "NA"){
  invisible(medpolish(data,  trace.iter = FALSE))
}


