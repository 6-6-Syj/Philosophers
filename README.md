# Philosophers


https://rom98759.github.io/Philosophers-visualizer/

##https://pages.mtu.edu/~shene/NSF-3/e-Book/index.html

##SSH
cat ~/.ssh/id_ed25519
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACDK4YpVCttHxrlsoVjC2Kg53+qblpwvc9K+SGEHKAbNNAAAAKCxlwOAsZcD
gAAAAAtzc2gtZWQyNTUxOQAAACDK4YpVCttHxrlsoVjC2Kg53+qblpwvc9K+SGEHKAbNNA
AAAED5JWuQSd2yS9PSOUE6xAM5hKQJvR81GXXQ4NVwkbUWZcrhilUK20fGuWyhWMLYqDnf
6puWnC9z0r5IYQcoBs00AAAAF21hZ2FuZC5qZXNzeUBvdXRsbG9rLmZyAQIDBAUG
-----END OPENSSH PRIVATE KEY---

cat ~/.ssh/id_ed25519.pub
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIMrhilUK20fGuWyhWMLYqDnf6puWnC9z0r5IYQcoBs00 magand.jessy@outllok.fr


./philo 2 800 200 200						personne ne meurt				✅​

./philo 5 800 200 200						personne ne meurt				✅​

./philo 4 410 200 200						personne ne meurt				✅​

./philo 4 500 200 1.2						argument invalide				✅​

./philo 4 0 200 200						argument invalide				✅​

./philo 4 -500 200 200						argument invalide				✅​

./philo 4 2147483647 200 200					personne ne meurt				✅​

./philo 4 214748364732 200 200					argument invalide				✅​

./philo 1 200 200 200						philo 1 ne prend qu'une fourchette		✅​
								et meurt au bout de 200 ms
	
./philo 4 310 200 200						un philo meurt, a 310 ms 			✅​

./philo 4 500 200 2147483647		  			un philo meurt au bout de 500 ms		✅​

./philo 4 200 210 20						un philo meurt, il faut afficher la 		✅
								mort avant 210 ms
	
./philo 5 800 200 200 7 				simulation end when each philo ate 7x			✅

philo impair time to sleep > time to eat									✅​

while eat bad timing death											✅​

Need to handle when sometimes steals each other forks								✅​

pthread_join quand pthread_create fail (join nb xready)								✅
