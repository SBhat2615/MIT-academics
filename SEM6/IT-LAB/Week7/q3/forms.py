from django import forms

class PublisherForm(forms.Form):
    name = forms.CharField(max_length=100)
    street = forms.CharField(max_length=200)
    city = forms.CharField(max_length=50)
    state = forms.CharField(max_length=50)
    country = forms.CharField(max_length=50)
    site = forms.URLField()

class AuthorForm(forms.Form):
    fname = forms.CharField(max_length=100, label="First Name")
    lname = forms.CharField(max_length=100, label="Last Name")
    email = forms.EmailField()

class BookForm(forms.Form):
    title = forms.CharField(max_length=200)
    pdate = forms.DateField(label="Publication Date")
    # Below 2 for foreign key mapping
    pname = forms.CharField(max_length=100,label="Publisher Name")
    anames = forms.CharField(max_length=400,label="Author First Name")

class BookSearch(forms.Form):
    title = forms.CharField(max_length=200, label="Enter book Name")

class AuthorSearch(forms.Form):
    fname = forms.CharField(max_length=100, label="Enter First Name")

class PublisherSearch(forms.Form):
    name = forms.CharField(max_length=100, label="Enter Publisher Name")