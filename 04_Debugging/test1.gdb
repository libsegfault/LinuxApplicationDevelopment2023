set pa off
b range.c:53

comm
  if I.curr % 5 == 0
    printf "@@@ %d %d %d %d", I.start, I.step, I.stop, I.curr
  end
  c
end

r 1 12 > /dev/null
