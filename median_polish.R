args <- commandArgs(TRUE)
fname <- toString(args[1])
justread <- toString(args[2])
data = read.table(paste("data/", fname, sep=""), sep = ',')
if (justread == "NA"){
  invisible(medpolish(data,  trace.iter = FALSE))
}


