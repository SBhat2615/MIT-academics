set ns [new Simulator]
set nf [open out.nam w]
ns nametrace-all $nf

$ns duplex-link link $n0 $n1 1mb 10ms DropTail