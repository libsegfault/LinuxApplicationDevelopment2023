set pa off
set $i = 1
b range.c:53

comm
  if $i >= 28 && $i <= 35
    printf "@@@ %d %d %d %d", I.start, I.step, I.stop, I.curr
  end
  set $i = $i + 1
  c
end

r -100 100 3 > /dev/null
