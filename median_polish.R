medpolish = function (x, eps = 0.01, maxiter = 10L, trace.iter = TRUE, na.rm = FALSE) 
{
  z <- as.matrix(x)
  nr <- nrow(z)
  nc <- ncol(z)
  t <- 0
  r <- numeric(nr)
  c <- numeric(nc)
  oldsum <- 0
  for (iter in 1L:maxiter) {
    rdelta <- apply(z, 1L, median, na.rm = na.rm)
    z <- z - matrix(rdelta, nrow = nr, ncol = nc)
    r <- r + rdelta
    delta <- median(c, na.rm = na.rm)
    c <- c - delta
    t <- t + delta
    cdelta <- apply(z, 2L, median, na.rm = na.rm)
    z <- z - matrix(cdelta, nrow = nr, ncol = nc, byrow = TRUE)
    c <- c + cdelta
    delta <- median(r, na.rm = na.rm)
    r <- r - delta
    t <- t + delta
    newsum <- sum(abs(z), na.rm = na.rm)
    converged <- newsum == 0 || abs(newsum - oldsum) < eps * 
      newsum
    if (converged) 
      break
    oldsum <- newsum
    if (trace.iter) 
      cat(iter, ": ", newsum, "\n", sep = "")
  }
  if (converged) {
    if (trace.iter) 
      cat("Final: ", newsum, "\n", sep = "")
  }
  else warning(sprintf(ngettext(maxiter, "medpolish() did not converge in %d iteration", 
                                "medpolish() did not converge in %d iterations"), maxiter), 
               domain = NA)
  names(r) <- rownames(z)
  names(c) <- colnames(z)
  ans <- list(overall = t, row = r, col = c, residuals = z, 
              name = deparse(substitute(x)))
  class(ans) <- "medpolish"
  ans
}

#data = read.table("data/test")
medpolish(data)
