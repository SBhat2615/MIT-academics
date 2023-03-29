from django.shortcuts import render

# Create your views here.

def carform(request):
    return render(request, 'carform.html')

def carresult(request):
    manufacturer = request.POST.get('manufacturer')
    model = request.POST.get('model')
    context = {
        'manufacturer': manufacturer,
        'model': model
    }
    return render(request, 'carresult.html', context)
