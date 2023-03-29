from django.shortcuts import render

# Create your views here.

def Firstpage(request):
    return render(request, 'firpage.html')

def Secondpage(request):
    brand = request.POST.get('brand')
    item = request.POST.get('item')
    quantity = int(request.POST.get('quantity'))
    
    if item == 'Mobile':
        price = 10000
    elif item == 'Laptop':
        price = 50000
    else:
        price = 0
    
    total = quantity * price
    
    context = {
        'brand': brand,
        'item': item,
        'quantity': quantity,
        'price': price,
        'total':total,
    }
    return render(request, 'secpage.html', context)

