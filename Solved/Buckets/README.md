# Buckets
Web

## Challenge 

Checkout my s3 bucket website!
http://tamuctf.s3-website-us-west-2.amazonaws.com/

Difficulty: easy

## Solution

We see a page without much info...

![screenshot.png](screenshot.png)

Easy challenge but only if [you know how AWS S3 Bucket URL works](https://docs.aws.amazon.com/AmazonS3/latest/dev/UsingBucket.html#access-bucket-intro).


	In a virtual-hosted–style URL, the bucket name is part of the domain name in the URL. For example:  
	http://bucket.s3.amazonaws.com
	http://bucket.s3-aws-region.amazonaws.com.

Hence, let's try without the region name

- http://tamuctf.s3.amazonaws.com/

And we [see this](page.xml) on the website

    <Contents>
        <Key>Dogs/CC2B70BD238F48BE29D8F0D42B170127/CBD2DD691D3DB1EBF96B283BDC8FD9A1/flag.txt</Key>
        <LastModified>2019-02-19T17:06:51.000Z</LastModified>
        <ETag>"0a2a337eda703cf59b4bc491dbc73621"</ETag>
        <Size>28</Size>
        <StorageClass>STANDARD</StorageClass>
    </Contents>

Visit that page and we see...

	flag{W0W_S3_BAD_PERMISSIONS}


> Reference: https://n0j.github.io/2017/10/02/aws-s3-ctf.html

## Flag

	flag{W0W_S3_BAD_PERMISSIONS}
