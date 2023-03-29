

# Create your views here.
from django.shortcuts import render, redirect
from django.contrib import messages

def register(request):
    if request.method == 'POST':
        username = request.POST.get('username')
        password = request.POST.get('password')
        email = request.POST.get('email')
        contact_number = request.POST.get('contact_number')
        if not username:
            messages.error(request, 'Username is required')
        else:
            request.session['username'] = username
            request.session['email'] = email
            request.session['contact_number'] = contact_number
            return redirect('success')
    return render(request, 'register.html')

def success(request):
    username = request.session.get('username')
    email = request.session.get('email')
    contact_number = request.session.get('contact_number')
    context = {
        'username': username,
        'email': email,
        'contact_number': contact_number,
    }
    return render(request, 'success.html', context)

