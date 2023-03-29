

# Create your views here.
from django.shortcuts import render, redirect

def first_page(request):
    if request.method == 'POST':
        request.session['name'] = request.POST.get('name')
        request.session['roll'] = request.POST.get('roll')
        request.session['subject'] = request.POST.get('subject')
        return redirect('second_page')
    return render(request, 'firstPage.html')

def second_page(request):
    name = request.session.get('name')
    roll = request.session.get('roll')
    subject = request.session.get('subject')
    context = {
        'name': name,
        'roll': roll,
        'subject': subject,
    }
    return render(request, 'secondPage.html', context)
