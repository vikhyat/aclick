require './xclick/xclick'

def click_loop(initial_wait, click_wait, rand_wait, &proc)
  c = 0
  sleep(initial_wait)
  loop do
    XClick::click
    proc.call(c+=1)
    sleep( click_wait + 2*rand_wait*(rand-0.5) )
  end
end

inw, clw, rdw = ARGV.map(&:to_f)
click_loop(inw, clw, rdw) do |c|
  puts c
end
