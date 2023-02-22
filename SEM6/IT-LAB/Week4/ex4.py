
class Solution:
    def get_string(self, str1):
        self.ip_str = str1
    
    def print_string(self):
        print(self.ip_str.upper())

s = Solution()
s.get_string(input('Enter a string: '))
s.print_string()