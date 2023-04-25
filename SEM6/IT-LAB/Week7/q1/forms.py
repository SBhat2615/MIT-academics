from django import forms

class CategoryForm(forms.Form):
    Name = forms.CharField(max_length=100)
    Visits = forms.IntegerField()
    Number_Of_Likes = forms.IntegerField(label='Likes')

class PageForm(forms.Form):
    Category = forms.CharField(max_length=100)
    Title = forms.CharField(max_length=100)
    Url = forms.URLField()
    View = forms.IntegerField()